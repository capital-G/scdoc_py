# scdoc_py

> A python wrapper for the SCDoc parser

This does not include a renderer (yet) because this would require a sclang runtime.
Yet it should be easy to transform the AST into another format or extract information out of it.

## Installation

> Sorry, no wheels yet - you have to build it yourself.

Make sure you have the Python development headers available on your system.

```shell
git clone --recurse-submodules https://github.com/capital-G/scdoc_py.git
cd scdoc_py
pip install .
```

## Usage

```python
>>> import scdoc_py
>>> x = scdoc_py.parse_file('HelpSource/Classes/AllpassC.schelp')
>>> x
<scdoc.DocNode 'DOCUMENT'>
>>> x.children
[<scdoc.DocNode 'HEADER'>, <scdoc.DocNode 'BODY'>]
```

## License

GPL-3.0
