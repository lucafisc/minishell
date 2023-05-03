#!./minishell
##!/bin/bash
echo "I'm a script"
wrong_cmd
export ARG=bla
echo $ARG
env | grep ARG
unset ARG
echo $ARG