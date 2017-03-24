#!/bin/bash

chmod +x make_blifs_no_D.sh
chmod +x make_D_blif.sh

caffeinate -i ./make_blifs_no_D.sh
caffeinate -i ./make_D_blif.sh


