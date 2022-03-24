# Implementing a FTP server using socket programming in C++

## Quick Overview
> In this project we're implementing a ftp server that can manage files using socket programming in c++


# How to run this project

- clone this repository
- use ``` make ``` command in server file
- use ``` make ``` command in client file

## What does this project do
here is a table of valid instructions that you can use as a client after running this program:

| Command | Description | Example |
| ------- | ----------- | ------- |
| pwd | shows the current working directory that you're in | pwd |
| mkd <file_path> | makes a new directory in the path that you entered | mkd /Users/nebula/Desktop/new_directory |
| dele -d <file_path> | deletes the directory of the given path | dele -d /Users/nebula/Desktop/new_directory |
| dele -f <file_path> | deletes the file of the given path | dele -d /Users/nebula/Desktop/new_file.txt |
| ls | shows a list of all the files in the current working directory | ls |
| cwd <file_path> | changes the current working directory path to the given path | cwd /Users/nebula/Desktop/another_directory |
| rename <from> <to> | renames the current directory/file name from ``` from ``` to ```to``` |
| retr <name> | downloads the given file from server | ** not done ** |
| help | shows a list of all the commands you can use in this project | help |
| quit | you can log out using this command | quit |
