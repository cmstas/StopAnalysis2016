#Condor for Babymaker

This will submit the babymaker in the parent directory on Condor

Instructions (no quotes):
  1.  set up core, babymaker and condor submission name you want to
      use in setup.sh and do source setup.sh
  2.  . copy.sh will assemble core, babymaker and make a tarball
      (in your $HOME directory) with the condor submission name you 
      specified in setup.sh instructions will also be printed out 
      in the end of this script to remind you what need to be modified
      in submitAll.sh in the next step.  Additionally, a directory named logs/ 
      will be created in the director where copy.sh is executed.  If 
      files already exist there, move them away, since the script checks
      for existing files, and will not create new ones if there.  This 
      is by design since the script will automatically resubmit failed
      jobs, and will skip (re)submission if the file exists already.

  3.  Edit submitAll.sh and condorFileTemplate following instructions printed in 
      step 2.
  
  4   Now run . submitAll.sh, it will submit jobs once so it is useful
      for debugging. 

  5. check for failed jobs and resubmit:
     ./checkAndResubmitAll.sh  cfg
  6. merge:
 

