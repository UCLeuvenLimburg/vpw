# General Hints and Tips
* You can only submit one file at a time. In Java, this means that if you need to work with multiple classes, you will have to make them [nested classes][https://docs.oracle.com/javase/tutorial/java/javaOO/nested.html]
* Writing text to a file/console is relatively slow and it is more efficient to output large blocks of text instead of single characters one at a time. For this reason, it often happens that your output gets stored in a temporary buffer (*caching*), which will get "flushed" only when enough data has been accumulated. This can be a problem at the contest: the server imposes a time limit, and after N seconds it kills the process running your code. This means your program does not get the chance to flush its output. If you are in a situation where the server tells you your program timed out and did not output anything, the caching is the most likely culprit. To remedy this, you need to *flush* your output. For example, in Java, you can write [`System.out.flush()`][https://docs.oracle.com/javase/7/docs/api/java/io/OutputStream.html#flush()] to force output to be written.


# Forking Instructions
1. Fork this repository using Bitbucket's web interface
2. Clone your fork, this copies all data to your local machine. **git clone https://*yourlogin*@bitbucket.org/*yourlogin*/ucll-vpw.**
3. In your local repository, create a new branch. **git branch *mybranch* **
4. Switch to this branch. **git checkout *mybranch* **
5. Tell git you want this local branch to also exist in the remote repository. **get branch -u origin/*mybranch* **
6. Write solution to some problem
7. Add the files to the staging area. **git add *file1* *file2* ...**
8. Commit the files to the local repository. **git commit -m "*Commit message*"**
9. Synchronize your local repository with your remote repository. **git push**
10. Using Bitbucket's web interface, go to this repository, create a pull request, and ask for your branch *yourlogin*/*mybranch* to be merged with fvogels/master
11. Wait for your pull request to be accepted.
12. Your work has been immortalized. Eternal glory and fame to you.