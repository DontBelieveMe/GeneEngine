cd Gene2
cd Documentation
call doxygen
cd ..
cd ..
git subtree split --branch gh-pages --prefix Gene2/Documentation/html
