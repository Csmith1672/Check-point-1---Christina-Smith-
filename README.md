Check-point-1---Christina-Smith-

Unix Shell Project (mysh)

name: Christina smith

Course

CS 350 - Operating Systems

Project Description

This project implements an easy Unix like shell in C++.

The shell accepts input from the user, interprets that input,

spawn creates child processes via fork(), and executes commands

using `execvp()

Shell accepts built-in commands and external Linux-like commands.

Features

Built-in Commands

cd → change directory

pwd → print working directory

exit →gives the exit shell command

External Commands

For example, the shell can execute Linux commands like this:

ls

cat

echo

mkdir

grep

Signal Handling

Supports Ctrl+C using
