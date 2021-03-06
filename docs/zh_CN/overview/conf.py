# -*- coding: utf-8 -*-
#
# Configuration file for the Sphinx documentation builder.
#
# This file does only contain a selection of the most common options. For a
# full list see the documentation:
# http://www.sphinx-doc.org/en/master/config

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------

project = u'AWTK概览'
copyright = u'2018, AWTK Development Team'
author = u'zq'

# The short X.Y version
version = u'0.0'
# The full version, including alpha/beta/rc tags
release = u'V0.0.0'

# -- General configuration ---------------------------------------------------

# If your documentation needs a minimal Sphinx version, state it here.
#
# needs_sphinx = '1.0'

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.doctest',
    'sphinx.ext.intersphinx',
    'sphinx.ext.todo',
    'sphinx.ext.coverage',
    'sphinx.ext.mathjax',
    'sphinx.ext.ifconfig',
    'sphinx.ext.viewcode',
	'sphinx.ext.autodoc',
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# The suffix(es) of source filenames.
# You can specify multiple suffix as a list of string:
#
# source_suffix = ['.rst', '.md']
source_suffix = '.rst'

# The master toctree document.
master_doc = 'index'

# The language for content autogenerated by Sphinx. Refer to documentation
# for a list of supported languages.
#
# This is also used if you do content translation via gettext catalogs.
# Usually you set "language" from the command line for these cases.
language = u'zh_CN'

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path .
exclude_patterns = [u'_build', 'Thumbs.db', '.DS_Store']

# The name of the Pygments (syntax highlighting) style to use.
pygments_style = 'sphinx'


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Theme options are theme-specific and customize the look and feel of a theme
# further.  For a list of options available for each theme, see the
# documentation.
#
# html_theme_options = {}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

# Custom sidebar templates, must be a dictionary that maps document names
# to template names.
#
# The default sidebars (for documents that don't match any pattern) are
# defined by theme itself.  Builtin themes are using these templates by
# default: ``['localtoc.html', 'relations.html', 'sourcelink.html',
# 'searchbox.html']``.
#
# html_sidebars = {}


# -- Options for HTMLHelp output ---------------------------------------------

# Output file base name for HTML help builder.
htmlhelp_basename = 'testdoc'


# -- Options for LaTeX output ------------------------------------------------

latex_elements = {

    'papersize': 'a4paper',
    'pointsize': '11pt',
	'extraclassoptions': 'oneside',# 防止新章节比较少时，新加一张空白页
	'footer': 'atendofbody',
    'fncychap' : u'\\usepackage[Sonny]{fncychap}',
	'passoptionstopackages': r'\PassOptionsToPackage{svgnames}{xcolor}',
	'sphinxsetup': 'attentionborder=3pt, attentionBorderColor={named}{Crimson}, attentionBgColor={named}{FloralWhite}, TitleColor={named}{MediumBlue}, noteborder=2pt,noteBorderColor={named}{Olive},',
    'releasename':  u' ',
    'preamble' : u'''
% 添加首行缩进，两个字符
\\usepackage{wallpaper} %使用wallpaper宏包
\\usepackage{titlesec}
\\usepackage{indentfirst}
\\usepackage{longtable}
\\usepackage{array}
\\usepackage{booktabs}
\\usepackage{colortbl}
\\usepackage{booktabs}
%%%%%%%%%%--------页码设置-----------%%%%%%%%%%%%
\\usepackage{fancyhdr} % 添加页眉页脚
\\usepackage{lastpage} %获得总页数
\\fancypagestyle{plain}{%默认每章的第一页的page style是plain，需要单独处理。
\\fancyfoot[CO,CE]{第 \\thepage\\ 页 共 \\pageref{LastPage}页} %居中显示页码，第 页 共 页
}
\\fancyfoot[CO,CE]{第 \\thepage\\ 页 共 \\pageref{LastPage}页} %居中显示页码，第 页 共 页
\\pagestyle{fancy}
%%%%%%%%%%--------页码设置-----------%%%%%%%%%%%%
\\setlength{\\parindent}{2em}
\\hypersetup{unicode=true}
\\usepackage{xeCJK}
\\setmainfont{Times New Roman}  %缺省英文字体
\\setCJKmainfont[BoldFont=SimHei,ItalicFont=KaiTi]{宋体}
\\setCJKsansfont{黑体}%serif是有衬线字体sans serif无衬线字体。
\\setmonofont{宋体} % 等寬字型
\\XeTeXlinebreaklocale "zh"
\\XeTeXlinebreakskip = 0pt plus 1pt minus 0.1pt
%\\renewcommand{\\headrulewidth}{0.7pt}
%\\renewcommand{\\footrulewidth}{0pt}
%%%%%%%%%%%%%%%------长表格设置-------%%%%%%%%%%%%%%
%替换原来的tabular环境,因为实际应用中很可能会使用长表格,这样出现长表格时,才不至于莫名其妙换页
\\renewenvironment{tabular}{\\begin{longtable}}{\\end{longtable}}%结束部分定义
%%%%%%防止因为使用长表格导致表索引与表部分重合
\\renewcommand{\\sphinxcaption}{\\caption}
\\renewcommand{\\sphinxaftercaption}{}
%%%%%%%%%%%%%%%------长表格设置-------%%%%%%%%%%%%%%
%%%%%%%%重载sphinxtableofcontents命令,使用系统的 tableofcontents 并且取消当前显示页码,重置为第0页
\\renewcommand{\\sphinxtableofcontents}{\\tableofcontents \\thispagestyle{empty} \\setcounter{page}{0}}
%%%%%%%%重载phantomsection命令,使得为空(不影响目录生成)
\\renewcommand{\\phantomsection}{}
\\docnum{UM3354}
\\releasedate{2018/12/01}
\\addto\\captionsenglish{
%    \\renewcommand{\\chaptername}{第 {\\thechapter} 章}
    \\renewcommand{\\contentsname}{目录}
    \\renewcommand{\\listfigurename}{插图目录}
    \\renewcommand{\\listtablename}{表格目录}
    \\renewcommand{\\refname}{参考文献}
    \\renewcommand{\\abstractname}{摘要}
    \\renewcommand{\\indexname}{索引}
    \\renewcommand{\\tablename}{表}
    \\renewcommand{\\figurename}{图}
 %  改变章节的格式
    \\titleformat{\chapter}{\color{red} \centering\Huge\\bfseries}{\color{red} 第\,\\thechapter\,章}{1em}{}
%%%%%%%%
%%%%%%%%   \\titleformat{\chapter}[block]{\center\Large\\bf}{\chaptername}{20pt}{}
%%%%%%%%   \\titleformat{\section}[block]{\large\\bf}{\\thesection}{10pt}{}
%%%%%%%%  \\renewcommand{\chaptername}{第 {\\thechapter}章}
%%%%%%%%   \\newcommand{\sectionname}{节}
%%%%%%%%   \\renewcommand{\\figurename}{图}
%%%%%%%%   \\renewcommand{\\tablename}{表}
%%%%%%%%   \\renewcommand{\\bibname}{参考文献}
%%%%%%%%   \\renewcommand{\contentsname}{目~录}
%%%%%%%%   \\renewcommand{\listfigurename}{图~目~录}
%%%%%%%%   \\renewcommand{\listtablename}{表~目~录}
%%%%%%%%   \\renewcommand{\indexname}{索~引}
%%%%%%%%   \\renewcommand{\\abstractname}{\Large{摘~要}}
%%%%%%%%   \\newcommand{\keywords}[1]{\\ \\ \\textbf{关~键~词}：#1}
}
'''
}

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class, ctexbook]).
latex_documents = [
   # (master_doc, 'h.tex', 'h Documentation',
   #  'xinrf1', 'manual'),  
   ('index', 'index.tex', u'{ FS应用文档}',
   u'\\unexpanded{ 赵启 }', 'ctexbook'),
]


# -- Options for manual page output ------------------------------------------

# One entry per manual page. List of tuples
# (source start file, name, description, authors, manual section).
man_pages = [
    (master_doc, 'test', u'test Documentation',
     [author], 1)
]


# -- Options for Texinfo output ----------------------------------------------

# Grouping the document tree into Texinfo files. List of tuples
# (source start file, target name, title, author,
#  dir menu entry, description, category)
texinfo_documents = [
    (master_doc, 'test', u'test Documentation',
     author, 'test', 'One line description of project.',
     'Miscellaneous'),
]


# -- Extension configuration -------------------------------------------------

# -- Options for intersphinx extension ---------------------------------------

# Example configuration for intersphinx: refer to the Python standard library.
intersphinx_mapping = {'https://docs.python.org/': None}

# -- Options for todo extension ----------------------------------------------

# If true, `todo` and `todoList` produce output, else they produce nothing.
todo_include_todos = True
