syntax on
set mouse=a
set nu
set ts=4
set sw=4
set smartindent
set cursorline
set hlsearch
set incsearch
set t_Co=256

nnoremap y ggyG

colorscheme afterglow

au BufNewFile *.cpp 0r ~/default_code/default.cpp | let IndentStyle = "cpp"
