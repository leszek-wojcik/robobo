#!/usr/bin/env python3

#
# gcc GTK+ Hello World
#
# build1.py
#
# Source: https://developer.gnome.org/gtk3/stable/gtk-getting-started.html
#
# Requirements:
#
#   Ubuntu: sudo apt install gcc ccache libgtk-3-dev
#
# This is the simplest possible version, using a single build phase and all the defaults.
#
# A single build phase works fine, and may be the best solution for small projects. However, it does
# not make use of Ninja's ability to parallelize builds and to track changes to individual files
# ("incremental" builds). Larger projects would generally build faster with a two-phase
# (compile/link) build. See build2.py for an example.
#

from ronin.cli import cli
from ronin.contexts import new_context
from ronin.gcc import GccBuild
from ronin.gcc import GccCompile
from ronin.gcc import GccLink
from ronin.phases import Phase
from ronin.pkg_config import Package
from ronin.projects import Project
from ronin.utils.paths import glob
from ronin.ninja import configure_ninja
from ronin.ninja import NinjaFile

with new_context(output_path_relative='build') as ctx:

    configure_ninja(ninja_command='ninja',
                    encoding='utf8',
                    file_name='build',
                    columns=100,
                    strict=False)

    utproject = Project(name='off target unit tests',variant='ut')
    
    unittestcompile = GccCompile(command='/usr/bin/g++')
    unittestcompile.define("DUPA",value=1)
    unittestcompile.add_include_path('src/')
    unittestlink = GccLink(command='/usr/bin/g++')
    unittestsources = glob('ut/*.cpp')
    unittestsources += (glob('src/simple.cpp'))

    Phase(  project=utproject,
            name='utcompile',
            executor=unittestcompile,
            inputs=unittestsources 
            )

    Phase(  project=utproject,
            name='utlink',
            executor=unittestlink,
            inputs_from=['utcompile'],
            extensions=[],
            output='unittests',
            run_output=1 if ctx.build.run else 0)

    ardproject = Project('target build')
    
    ardcompile = GccCompile(command='/usr/bin/clang++')
    ardcompile.define("DUPA",value=1)
    ardlink = GccLink(command='/usr/bin/clang++')
    ardsources = glob('src/*.cpp')

    Phase(  project=ardproject,
            name='ardcompile',
            executor=ardcompile,
            inputs=ardsources)

    Phase(  project=ardproject,
            name='ardlink',
            executor=ardlink,
            inputs_from=['ardcompile'],
            extensions=[],
            output='ard',
            run_output=1 if ctx.build.run else 0)

#    cli(utproject,ardproject)
    n = NinjaFile(utproject,file_name='utproject')
    n.generate()

    n = NinjaFile(ardproject,file_name='ardproject')
    n.generate()

