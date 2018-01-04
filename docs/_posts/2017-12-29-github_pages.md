---
layout: post
title:  "Enabling Github Pages for Arduino Project"
date:   2017-12-29 20:19:00 +0100
description: Github pages allows you to host static webpages for your Github
project. Following guide will walk you through Github pages creation using Yekyll.
categories: githubpages
---

If you would like to start your Github hosted page I will briefly describe what I've
done. You can see my code in repository so I think this could be useful in case
you are stuck. 

# Why would you even like to use Github pages? 
I assume nowdays if you want to share your project you need a webpage.
If you don't have one nobody will pay attention to your work unless you are Apple or
Google.  I think it is extremely useful to get webpage created out from your
repository so you keep everything in one place. This way your work is efficient
and streamlined. Github provides you an easy way to get your web page hosted.
Web page generated this way is static so don't expect any business logic at
server side - this is purely for presentation and nothing more.  

Let me tell you a few words about my process of webpage creation.  Please take
a look into my repository. In Github project settings I've selected to host
`docs` folder from my `master` branch. My typical activity is adding new posts
in `docs/_posts/`. Each post is just new `.md` text file.  `.md` file
extensions stands for MarkDown format. You can find details on markdown format
[here](https://guides.github.com/pdfs/markdown-cheatsheet-online.pdf). It is
convenient and simple. 

# Lets get started. 
Although it seems like Github provide easy to use guide I fell into several
pitfalls. I'm not so into Ruby technology that is probably a reason. But really
you don't need to actually have a deep understating of Ruby in order to use
Github pages. 

My suggestion is to to do Jekyll compile at your side before starting any work
in your repository. This will basically reduce number of really unnecessary
commits and save your time. Secondly be advised that Jekyll compile of your
pages at Github are not happening right away. It make take minutes until
changes you push to your repository are visible on your browser. Once again its
easier to do compile at your side. 

Spent some time on installing Ruby and Jekyll environment in your PC. This
topic is well covered on Github documents
[here](https://jekyllrb.com/docs/quickstart/). Be advised that you need to
install additional software in your pc to able compile and run Jekyll. In Linux
you will have to download multiple packages with source code of libraries
requested by Jekyll and its dependencies. Usually errors displayed by `gem
install` are sufficient to realize what is actually missing. For myself I
needed to install zlib source code packages in my ubuntu Linux. For that
particular package installation I run `sudo apt-get install zlib1g-dev`. 

When finally you are able to successfully execute following set of commands:
```bash
jekyll new my-awesome-site
cd my-awesome-site
bundle exec jekyll serve
```
you are ready for some more explanation about themes.

# Themes
Before selecting theme  be advised that only subset of themes are prepared to
do the work that is provided by default `minima` theme.  For myself I was truly
after blog functionality. Minima theme provides you layouts called `page`,
`post` and `home` unlike others just provide `default`. So if you are looking
for fast start stick to minima. If you change it you need to start with
`default` layout and then self create others in order to do a single blog post. 

 
