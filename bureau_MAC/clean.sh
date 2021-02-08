#!/bin/sh

rm -r ~/Library/Caches/*
rm ~/.zcompdump*
rm -rf ~/Library/**.42_cache_bak_**
rm -rf ~/**.42_cache_bak_**
brew cleanup
