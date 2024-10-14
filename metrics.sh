#!/usr/bin/env bash

# Helper script to run metrix++ and collect maintainability data

# Add Python's venv to the PATH
export PATH="$PATH:$(pwd)/venv/bin"

metrix++ collect --scmis --std.code.complexity.cyclomatic --std.code.lines.code GameOfLife
metrix++ view --db-file=metrixpp.db

