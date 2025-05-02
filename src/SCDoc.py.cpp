#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <SCDoc.h>
#include <vector>
#include <optional>

namespace py = pybind11;

// transform raw DocNode** into std::vector<DocNode>
// by using a custom struct
typedef struct PyDocNode {
    std::string id;
    std::string text;
    struct std::vector<PyDocNode> children;
} PyDocNode;

PyDocNode toDocPyNode(const DocNode* node) {
    PyDocNode py_node;

    if (node->id) py_node.id = node->id;
    if (node->text) py_node.text = node->text;

    for (int i = 0; i < node->n_childs; ++i) {
        py_node.children.push_back(toDocPyNode(node->children[i]));
    }

    return py_node;
}

PyDocNode parse_file(std::string &file_name) {
    DocNode* node = scdoc_parse_file(file_name, SCDOC_PARSE_FULL);
    if (node == nullptr) {
        throw std::runtime_error("Couldn't parse file!");
    }
    return toDocPyNode(node);
}

PYBIND11_MODULE(_scdoc_py, m) {
    m.doc() = "SCDoc binding for Python";
    m.def("parse_file", &parse_file, "Parse scdoc file");

    py::bind_vector<std::vector<PyDocNode>>(m, "DocNodeVector");

    py::class_<PyDocNode>(m, "DocNode")
        .def_readonly("id", &PyDocNode::id)
        .def_readonly("text", &PyDocNode::text)
        .def_readonly("children", &PyDocNode::children)
        .def("__repr__",
            [](const PyDocNode &a) {
                return "<scdoc.DocNode '" + a.id + "'>";
            }
        );
}
