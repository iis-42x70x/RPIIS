#!/bin/bash
# author: https://github.com/danilyanich

set -euxa pipefail

branches=$(cat branches)

echo "$branches" | while read branch
do
  git checkout "$branch"
  git pull --rebase origin main
  git push origin "$branch" --force-with-lease
done

git checkout main
