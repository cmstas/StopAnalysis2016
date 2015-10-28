#Condor for Babymaker

This will submit the babymaker in the parent directory on Condor

Instructions (no quotes):
  1.  edit setup.sh to include the path and name of the babyMaker, CORE,
      output directory (COPY_DIR), and scratch dir (SCRATCH_DIR, should be on
      /data/tmp) location that will be used for log file output and 
      staging for merging babies. 
      Additionally, you can set the name of the tarball that will be used
      to ship the executables to the condor node via $CONDOR_DIR_NAME


  2.  To submit condor jobs to make Stop Babies, execute ". copy.sh" to 
      copy stuff from the parent directory to the batch directory.  
      This will be a folder in your $SCRATCH_DIR directory, named: 
      $CONDOR_DIR_NAME.  Additionally, a directory named logs/ 
      will be created in $SCRATCH_DIR.  If files already exist there, 
      move them away, since the script checks for existing files, 
      and will not create new ones if there.  This is by design since 
      the script will automatically resubmit failed jobs, and will skip 
      (re)submission if the file exists already.


  3.  Open batch.sh and modify the fields at the top to specify which 
      babies should be produced ($sampleList_in).   
	  
      
  4.  In condorFileTemplate, change line 12 to your email address for
      notifications from the condor queue about the job ending/failing     


  5.  If you would like to test your setup, simply run ". batch.sh" in 
      order to submit jobs from $sampleList_in.  If this is the first time
      running, it may be worthwhile to only run on 1 sample to ensure
      that nothing fails.  After all jobs run, you can execute ". batch.sh" 
      again to test for zombies, resubmit jobs, and merge babies.  batch.sh
      does the following:
        a) 1 CMS3 file = 1 baby = 1 condor job
        b) check output direcotory ($COPY_DIR) to see if the baby already exists,
           if so, do nothing, move onto the next sample
        c) check if baby is already is running, if running do nothing, move
           onto next sample
        d) if all babies in sampleList_in are complete, and none are running,
           check for zombies.  This will create a list of files notZombies.txt 
           in the logs/ subdir in $SCRATCH_DIR.  This is done for the case of
           many files, so the zombie checking is only done when necessary
        e) if no zombies exist, merge files.  Merging is limited to a 
           number of input files set in mergeAll.sh.  Currently it is
           set for 100 files, in order to stay under the 100GB limit
           for writing an individual file.  Output is staged in the 
           $SCRATCH_DIR before being moved to $COPY_DIR/merged/ when
           all files are merged.


  6.  ". makeBabies.sh" will continuously run batch.sh.  Just let it run, 
      it will quit when all babies exist.  It will also merge them for 
      you at the end.  Run this command in a screen session.

