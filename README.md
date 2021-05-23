# SCC Toolkit

The SCC Toolkit binary contains the assembler and dissasembler for the
SCC4 format. The future plan for this toolkit is to have a static linker
and an optimizer. Creating the linker would be easier, because all you
have to to is provide an object ID offset and check for name conflicts,
because all SCC4 code is by default position independent. The optimizer
would be a bigger project.

This is created to be easy to use by other tools, like the Salt Compiler
which could only compile to Salt Assembly, and let the scc toolkit convert
it into bytecode. By default, the assembled file gets written to stdout
so it can be piped and used in scripts. That's why you need to specify
the output file.

```
$ scc -a code.sa -o code.scc
```
