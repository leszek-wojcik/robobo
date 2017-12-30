---
layout: post
title:  "Github Pages"
date:   2017-12-29 20:19:00 +0100
categories: githubpages
---

If you would like to start your github hosted page I will briefly describe what I've
done. You can see my code in repository so I think this could be useful. 

# Why would you even like to use github pages? 
I assume nowdays if you want to share your project you need a webpage.
Otherwise nobody will pay attention to your work unless you are Apple or
Google.  I think it is extremely useful to get webpage created out from your
repository so you keep everything in one place. This way your work is efficient
and streamlined. Github provides you an easy way to get your web page hosted.
Web page generated this way is static so don't expect any business logic at
server side - this is purely for presentation and nothing more.  

Few words about my process of webpage creation.  Please take a look into my
repository. In github project settings I've selected to host ```docs``` folder
from my ```master``` branch. My typical activity is addign new posts in 
```docs/_posts/```. Each post is just new ```.md``` text file. ```.md``` file
extensions stands for MarkDown format. You can find details on markdown format
[here] (https://guides.github.com/pdfs/markdown-cheatsheet-online.pdf). It
convinient and simple. 

# Lets get started. 
Although it seems like github provide easy to use guide I fell into several
pitfalls. I'm not so into Ruby technology that is probably a reason. You don't
need to actually have a deep understating of it to use it. 

My suggestion is to to do Jekyll compile at your side before starting any
work in your repository. This will basically reduce number of really
unnecessary commits. Secondly be advised that Jekyll compile of your pages are
not happening right away. It make take minutes until changes you push to your
repository are visible on your browser.

Spent some time on installing ruby and Jekyll environment in your PC. This topic is well
covered on github documents [here](https://jekyllrb.com/docs/quickstart/). Be
advised that you need to install additional software in your pc to able compile
and run http server. In Linux you will have to download multiple packages with
sourcode of libraries requested by Jekyll. Usually erros displayed by ```gem
install``` are sufficient to realize what is actually missing. For myslef I
needed to install zlib source code packages in my ubuntu Linux. For that
particular package installation I run ```sudo apt-get install zlib1g-dev```. 

When finally you are able to sucessfully execute following set of commands:
```bash
jekyll new my-awesome-site
cd my-awesome-site
bundle exec jekyll serve
```
you are ready for some more explanation about themes.

# Themes
Before selecting theme you would like to use be advised that only subset of
themes are prepared to do the work that is provided by default ```minima``` theme.
For myself I was truly after blog functionality. Minima theme provides you
layouts called ```page```, ```post``` and ```home``` unlike others just provide
```default```. So if you are looking for fast start stick to minima. If you
change it you need to start with ```default``` layout and then self create
others in order to do a single blog post. 

 
