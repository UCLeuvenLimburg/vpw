\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{ucll-slides}[2016/05/21]

\DeclareOption*{\PassOptionsToClass{\CurrentOption}{beamer}}

\ProcessOptions\relax


\LoadClass{beamer}

\RequirePackage{graphicx}
\RequirePackage{pxfonts}
\RequirePackage{tikz}
\RequirePackage{calc}
\RequirePackage{listings}
\RequirePackage{booktabs}
\RequirePackage{url}
\RequirePackage{framed}
\RequirePackage{hyperref}
\RequirePackage{cleveref}
\RequirePackage{bbding}
\RequirePackage{wasysym}

\usetikzlibrary{shadows,calc,shapes}



\mode<presentation>
\usetheme[height=.75cm,compress]{Singapore}


\institute[UCLL]{UC Leuven Limburg}


\newcommand{\toc}{
  \begin{frame}
    \tableofcontents[sectionstyle=show/shaded,subsectionstyle=show/shaded/hide]
  \end{frame}
}

\newcommand{\link}[2]{\href{#1}{{\color{blue}#2}}}
