#!/bin/bash

if [[ ! -z "$(git status --porcelain -uno | grep -v -e 'cmake-build-debug' -e '.idea' )" ]]; then
    echo "Cannot clean git while repo files were changed but not comitted" >&2;
    exit -1;
fi

read -p "Enter branch to implement fixes to [main]: " branch
branch=${branch:-main}
git checkout $branch
git pull

if [ ! -f ./.gitignore ]; then
    echo ".gitignore missing, creating and commiting the file"
    echo "**/cmake-build-debug/" > ./.gitignore
    echo "**/.idea/" >> ./.gitignore
    echo "**/main.out" >> ./.gitignore
    echo "**/test.out" >> ./.gitignore
    echo "**/*.res" >> ./.gitignore
    echo "**/test_results.html" >> ./.gitignore
    git add ./.gitignore
    git commit -m "Add gitignore"
fi
git rm --cached -r **/cmake-build-debug/
git commit -m "Remove cmake-build-debug from git index"
git rm --cached -r **/.idea/
git commit -m "Remove idea folder from git index"
git rm --cached **/*.res
git commit -m "Remove tests' output from git index"
git rm --cached **/test_results.html
git commit -m "Remove tests' report from git index"
git rm --cached **/main.out
git commit -m "Remove wet compiled executable from git index"
git rm --cached **/test.out
git commit -m "Remove wet compiled testing executable from git index"
git push
