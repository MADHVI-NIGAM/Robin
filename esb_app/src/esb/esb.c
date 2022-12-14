#include<stdio.h>
#include<stdlib.h>
#include "email.h"
#include "esb.h"
#include <sqlite3.h>
/**
 * TODO: This is to be implemented separately.
 */
bmd parse_bmd_xml(char* bmd_file_path) {
    bmd b;
    bmd_envelop envl;
    envl.sender_id = "TEST-GUID-1";
    envl.destination_id = "TEST-GUID-2";
    envl.message_type = "TEST-GUID-3";

    b.envelop = envl;
    b.payload = "Some data here";
    return b;
}


static int is_bmd_valid(bmd b)
{
    int valid = 1; // 1 => vaild, -1 => invalid
    // TODO: Implement the validation logic here
    if(envl.sender_id==NULL || envl.destination_id==NULL || envl.message_id==NULL)
    {
        valid=-1;
    }
    return valid;
}

static int queue_the_request(bmd b)
{
    int success = 1; // 1 => OK, -1 => Error cases
    /** 
     * TODO: Insert the envelop data into esb_requests table,
     * and implement other logic for enqueueing the request
     * as specified in Theory of Operation.
     */
    rc = sqlite3_open("test.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }
   sql="INSERT INTO ESB_REQUEST(SENDER_ID,DEST_ID,MESSAGE_TYPE)"
        "VALUES(envl.sender_id,envl.destination_id,envl.message_type)"
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
    sqlite3_close(db);
    return success;
}

/**
 * This is the main entry point into the ESB. 
 * It will start processing of a BMD received at the HTTP endpoint.
 */
int process_esb_request(char* bmd_file_path) {
    int status = 1; // 1 => OK, -ve => Errors
    printf("Handling the BMD %s\n", bmd_file_path);
    /** TODO: 
     * Perform the steps outlined in the Theory of Operation section of
     * the ESB specs document. Each major step should be implemented in
     * a separate module. Suitable unit tests should be created for all
     * the modules, including this one.
     */
    // Step 1:
    bmd b = parse_bmd_xml(bmd_file_path);

    // Step 2:
    if (!is_bmd_valid(b))
    {
        //TODO: Process the error case
        printf("BMD is invalid!\n");
        status = -2;
    }
    else
    {
        // Step 3:
        status = queue_the_request(b);
    }
    
    return status;
}
