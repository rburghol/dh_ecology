library("hydrotools")
library("httr")

basepath = "/var/www/R"
source(paste(basepath,"config.R", sep="/"))

data_in = "C:/home/git/dh_ecology_git/data"
fname = "for_batch_upload_2021-12-02.txt"
  
tdb_dat <- read.csv(paste(data_in, fname, sep="/"), sep = "\t")

