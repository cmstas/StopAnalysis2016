#Condor for Babymaker

This will submit the babymaker in the parent directory on Condor

Instructions (no quotes):
  1.  Follow instructions in parent directory; this should work locally. 
      Make sure your CORE and Software/MiniFWLite is up to date.
      
      NB:  This setup assumes that CORE, Software, and StopAnalysis 
      	   directories are all located in in the directory 
	   CMSSW_X_Y_Z/src.  If this is not the case for you, then you 
	   will need to modify your local area to fit this, OR modify the 
	   file: condorExecutable.sh, lines 48-65 so that the movement 
	   between directories will work correctly.  Also, if changing 
	   the locations of CORE and Software, be sure to update the 
	   paths in the StopBabyMaker Makefile, lines 24-25, by correctly 
	   setting the variables: COREPATH, and FWLIBPATH

  2.  To submit condor jobs to make Stop Babies, execute ". copy.sh" to 
      copy stuff from the parent directory to the batch directory.  
      This will be a folder in your $HOME directory, named: 
      forCondor_stopBabyMaker.  Additionally, a directory named logs/ 
      will be created in the director where copy.sh is executed.  If 
      files already exist there, move them away, since the script checks
      for existing files, and will not create new ones if there.  This 
      is by design since the script will automatically resubmit failed
      jobs, and will skip (re)submission if the file exists already.

  3.  Open batch.sh and modify the fields at the top to specify which 
      babies should be produced (line 6).  Line 15 will also specify 
      the directory on /hadoop/ where the output baby files will be
      copied to.

  4.  In condorFileTemplate, change line 12 to your email address for
      notifications from the condor queue about the job ending/failing     

  5.  ". makeBabies.sh" to submit.  Just let it run, it will quit when 
      all babies exist.  It will also merge them for you at the end,
