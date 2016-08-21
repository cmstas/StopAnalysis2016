#Condor submission for combine limit setting

Instructions:
  1.  modify setup.sh appropriately: only entries between 'NAME' and
      'fakedata' as well as your username, and SCRATCH_DIR/COPYDIR
      should be modified.
  2.  run '. setup.sh'
  3.  run '. batch.sh'
  4.  Wait until rootfiles arrive. In fact - you cannot run next
      limit/significance until the jobs are running - as the datacards
      are stored locally in this directory for submission.
  5. When done, clean up: '. cleanup.sh'

To be done: Implement checks if things were submitted and/or are
finished, so that step 4 doesn't depend on intelligence of the user.
