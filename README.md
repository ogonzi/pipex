<h1 align="center">
	Pipex
</h1>

<p align="center">
	<b><i>Pipe handling in UNIX.</i></b><br>
</p>
<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/ogonzi/pipex?color=lightblue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/ogonzi/pipex?color=critical" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/ogonzi/pipex?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/ogonzi/pipex?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/ogonzi/pipex?color=green" />
</p>

<h3 align="center">
	<a href="#about">About</a>
	<span> · </span>
	<a href="#features">Features</a>
	<span> · </span>
	<a href="#usage">Usage</a>
</h3>

---

## About

This project is about handling pipes, more specifically, it is about simulating the pipe "|" operator in C. Through this project multiple concepts about UNIX processes in C are learnt as an introduction to concurrent programming.

## Features

### Mandatory

- Handles 4 arguments, input and output files (first and last), and two commands (middle). Behaves like:
```shell
< file1 cmd1 | cmd2 > file2 
```

### Bonus

- Handles multiple pipes. Behaves like:
```shell
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2 
```
<p align="center">
	<img src="https://github.com/ogonzi/push_swap/blob/dev/scheme.jpg" />
</p>
- Supports << and >> when the first parameter is "here\_doc". Behaves like:
```shell
cmd << LIMITER | cmd1 >> file 
```

## Usage

Usage under construction

## Resources

- [Half-duplex UNIX pipes](https://tldp.org/LDP/lpg/node9.html#SECTION00720000000000000000)
- [Understanding pipes in UNIX](https://medium.com/swlh/understanding-pipes-in-unix-with-a-sample-implementation-9fe110d36412)
- [UNIX Processes in C](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)

## Known bugs


## Authors

- [@ogonzi](https://www.github.com/ogonzi)

