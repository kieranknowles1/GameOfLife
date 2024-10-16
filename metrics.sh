#!/usr/bin/env bash

# Helper script to run metrix++ and collect maintainability data

source venv/bin/activate

metrix++ collect --scmis \
    --std.code.complexity.cyclomatic \
    --std.code.lines.code \
    GameOfLife
metrix++ view --db-file=metrixpp.db

metrix++ limit \
    --max-limit=std.code.lines:code:15:function
