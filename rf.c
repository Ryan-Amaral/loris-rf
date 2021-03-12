/*
Random notes up heres:

When in send mode, rf module just does stuff whenever told.
In receive mode, rf module always listens.
*/

// initializes the module, and returns status code
int initialize(){

}

// constantly running loop to receive data
// should be ran in different thread if can receive and send simultaniously
void _receive(){
    while(doReceive){
        // get stuff
    }
}