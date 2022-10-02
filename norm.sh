#!/bin/bash

python3 -m venv venv
source venv/bin/activate
pip install norminette
norminette $PWD/*.c $PWD/*/*.c | grep Error
deactivate
