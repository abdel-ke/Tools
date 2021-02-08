#!/bin/sh
#brew uninstall docker -y
#brew uninstall docker-machine -y
rm -rf ~/.brew
rm -rf /goinfre/abdel-ke/.brew
rm -rf /goinfre/abdel-ke/virtualbox
rm -rf ~/Library/VirtualBox
mv ~/Library/VirtualBox/ /goinfre/abdel-ke
ln -s /goinfre/abdel-ke/VirtualBox ~/Library
git clone https://github.com/Homebrew/brew ~/.brew
echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc
source $HOME/.zshrc
mv ~/.brew /goinfre/abdel-ke
ln -s /goinfre/abdel-ke/.brew ~/
brew install docker
brew install docker-machine
docker-machine rm default
docker-machine create --driver virtualbox default
docker-machine env default
eval $(docker-machine env default)
docker run -it debian

