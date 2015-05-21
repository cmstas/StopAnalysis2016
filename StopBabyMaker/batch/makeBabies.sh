#!/bin/bash

while (( "1" == "1" )); do . batch.sh; if [ "$?" == "1" ]; then break; fi; done
