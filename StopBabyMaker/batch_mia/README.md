#Condor for Babymaker

This will submit the babymaker in the parent directory on Condor

Instructions (no quotes):
  1.  set up core, babymaker and condor submission name you want to
      use in setup.sh and do source setup.sh
  2.  . copy.sh will assemble core, babymaker and make a tarball
      (in your $HOME directory) with the condor submission name you 
      specified in setup.sh instructions will also be printed out 
      in the end of this script to remind you what need to be modified
      in batch.sh in the next step.  Additionally, a directory named logs/ 
      will be created in the director where copy.sh is executed.  If 
      files already exist there, move them away, since the script checks
      for existing files, and will not create new ones if there.  This 
      is by design since the script will automatically resubmit failed
      jobs, and will skip (re)submission if the file exists already.

  3.  Open batch.sh and modify the fields at the top to specify which 
      babies should be produced (line 6).  Line 15 will also specify 
      the directory on /hadoop/ where the output baby files will be
      copied to.	  
	  b. If you want to load a different sample.dat file please modify
      l.64 and l.74.

  4.  In condorFileTemplate, change line 12 to your email address for
      notifications from the condor queue about the job ending/failing     
  
  5   Now run . batch.sh, it will only submit jobs once so it is useful
      for debugging. 

  6.  ". makeBabies.sh" to submit.  Just let it run, it will quit when 
       all babies exist.  It will also merge them for you at the end,
	   b. run this command in a screen session.

