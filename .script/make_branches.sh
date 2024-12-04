#!/bin/bash
# author: https://github.com/danilyanich

set -euxa pipefail

branches=$(cat branches)

echo "$branches" | while read branch
do
  git checkout -b "$branch"
  git push origin "$branch"
done

git checkout main
