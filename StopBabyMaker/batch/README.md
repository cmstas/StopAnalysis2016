#Condor for Babymaker

This will submit the babymaker in the parent directory on Condor

Instructions (no quotes):
  1.  edit setup.sh to include the information:
        A) path and directory name of the babyMaker, 
             $MAKER_NAME and $MAKER_PATH 
        B) path and directory name of CORE (should just be CORE)
             $CORE_NAME and $CORE_PATH
        C) output directory path and name 
	     $COPY_NAME and $COPY_PATH
	D) scratch dir (should be on /data/tmp), user will need to
           create a folder for this, and it will be used for 
           log file output and staging for merging babies 
             $SCRATCH_NAME and $SCRATCH_PATH
        E) name of the tarball that will be used to ship the 
           executables to the condor node
             $CONDOR_DIR_NAME
        F) email for condor submision var notfiy_user, set in 
           condorFileTemplate
             $USER_EMAIL 
      
  2.  After editing setup.sh, execute it:
        > . setup.sh

  3.  To submit condor jobs to make Stop Babies, execute copy.sh:
        > . copy.sh 
      
      This will copy the babyMaker code to $SCRATCH_DIR/$CONDOR_DIR
      Additionally, a directory named $SCRATCH_DIR/logs/.

  4.  Open batch.sh and modify the fields at the top to specify which 
      babies should be produced ($sampleList_in).   
	  
  
  5.  If you would like to test your setup, simply run batch.sh once:
        > . batch.sh 
      This will submit jobs from $sampleList_in.  If this is the first time
      running, it may be worthwhile to only run on 1 sample to ensure
      that nothing fails.  After all jobs run, you can execute batch.sh
      again to test for zombies, resubmit jobs, and merge babies.  

  NB: batch.sh does the following:
        A) 1 CMS3 file = 1 baby = 1 condor job
        B) Check output direcotory ($COPY_DIR) to see if the baby 
	   already exists, if so, do nothing, move onto the next file 
        C) Check if baby is already is running, if running do nothing, and
           move onto the next file
        D) If all babies in sampleList_in are complete, check for zombies.
	   This will create a list of files notZombies.txt 
           in the $SCRATCH_DIR/logs/ subdir.  This is done for the case of
           many files, so the zombie checking is only done when necessary.
        E) If no zombies exist, merge files.  Merging is limited to a 
           number of input files set in mergeAll.sh.  Currently it is
           set for 100 files, in order to stay under the 100GB limit
           for writing an individual file.  Output is staged in the 
           $SCRATCH_DIR before being moved to $COPY_DIR/merged/ when
           all files are merged.

  6.  makeBabies.sh will continuously run batch.sh.  
        > . makeBabies.sh 
      Just let it run, it will quit when all babies exist.  It will also 
      merge them for you at the end.  Run this command in a screen session.

