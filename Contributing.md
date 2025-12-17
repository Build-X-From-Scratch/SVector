# Introduction

this project maybe still have an issue,therefore i need help you guys to fix issue with
pull request

# Clone Repo

Clone this repo to your local,with this command

```bash
git clone https://github.com/Build-X-From-Scratch/SVector.git
```
# Create branch

for add fiture,fix bug and so on, we need a new branch separate from the main branch.following this command

```bash
git chechkout -b <frefix: feat,fix,chore,refactor,test>/<name_branch>
```

example

```bash
git checkout -b feat/vector_bool
```

# Commit

Only commit code where you have made changes,example `header` then 

```bash
git commit header/vector.hpp -m "commit msg"
```

after this,push to repo fork following this command

```bash
git push origin main
```


# Optional

you cant add upstream remote and add changes in repo to your local,use this command to add
upstream remote
```bash
git remote add upstream https://github.com/Build-X-From-Scratch/SVector    
 ```

check with command
```bash
git remote -v
```

if succes,you cant try
```bash
git fetch upstream
```
if there changes you can merge with local following this command
```bash
git merge upstream <you_branch>
```