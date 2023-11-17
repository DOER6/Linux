all: read write

read: read_pipe.c
	gcc $< -o $@   
##使用 gcc 编译器，将规则的第一个依赖项作为源文件，编译并生成目##标文件，将目标文件命名为规则的目标文件。

write: write_pipe.c
	gcc $< -o $@

clean:
	rm -rf read write

