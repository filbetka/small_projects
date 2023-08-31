alias pip=pip3
alias vi=vim

function gits
    git status
end

function gitc
    git commit -m $argv
end

function aptll
    sudo apt-get install $argv
end

