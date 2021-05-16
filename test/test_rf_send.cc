/*
Used to test the functionality of rf_send.
*/

#include <stdio.h>
#include "../src/rf_send.h"

bool test_init(){
    printf("Testing init.\n");
    rf::QueuesPackage* qp = rf::init(5, 100);
    if(qp->n_queues != 5){
        printf("Error: Wrong queue size.\n");
        return false;
    }
    if(qp->chunk_size != 100){
        printf("Error: Wrong chunk size.\n");
        return false;
    }

    printf("Success: init.\n");
    return true;
}

bool test_add_to_queue(){
    printf("Testing add_to_queue.\n");
    rf::QueuesPackage* qp = rf::init(5, 100);

    printf("Testing add image to queue.\n");
    printf("%d\n", qp->id_count);
    rf::add_to_queue(true, "image.txt", 2, qp, 0);
    printf("%d\n", qp->id_count);
    if(qp->queues[2].front().is_image == false){
        printf("Error: Image didn't save as image.\n");
        return false;
    }
    if(qp->queues[2].front().id != 1){
        printf("Error: ID incorrect.\n");
        return false;
    }

    printf("Testing add text to queue.\n");
    printf("%d\n", qp->id_count);
    rf::add_to_queue(false, "test_message", 0, qp, 0);
    printf("%d\n", qp->id_count);
    if(qp->queues[0].front().is_image == true){
        printf("Error: Text didn't save as text.\n");
        return false;
    }
    if(qp->queues[0].front().id != 2){
        printf("Error: ID incorrect.\n");
        return false;
    }

    printf("Success: add_to_queue.\n");
    return true;
}

bool run_individual_tests(){
    bool success_init = test_init();
    bool success_add_to_queue = test_add_to_queue();

    return success_init && success_add_to_queue;
}

bool test_scenario_1(){
    rf::QueuesPackage* qp = rf::init(5, 100);

    printf("Adding things to queues.\n");

    rf::add_to_queue(true, "image1.txt", 0, qp, 0);
    rf::add_to_queue(true, "image2.txt", 1, qp, 0);
    rf::add_to_queue(true, "image3.txt", 2, qp, 0);
    rf::add_to_queue(true, "image4.txt", 2, qp, 0);

    rf::add_to_queue(false, "message 1", 0, qp, 0);
    rf::add_to_queue(false, "message 2", 1, qp, 0);
    rf::add_to_queue(false, "message 3", 2, qp, 0);
    rf::add_to_queue(false, "message 4", 2, qp, 0);

    printf("Queue 0 expected: %d, actual: %ld.\n", 2, qp->queues[0].size());
    printf("Queue 1 expected: %d, actual: %ld.\n", 2, qp->queues[1].size());
    printf("Queue 2 expected: %d, actual: %ld.\n", 4, qp->queues[2].size());
    printf("Queue 3 expected: %d, actual: %ld.\n", 0, qp->queues[3].size());
    printf("Queue 4 expected: %d, actual: %ld.\n", 0, qp->queues[4].size());

    printf("\nTesting removals.\n");

    rf::truncate_queue(qp, 0);
    rf::truncate_queue(qp, 2);
    rf::empty_queue(qp, 1);

    printf("Queue 0 expected: %d, actual: %ld.\n", 1, qp->queues[0].size());
    printf("Queue 1 expected: %d, actual: %ld.\n", 0, qp->queues[1].size());
    printf("Queue 2 expected: %d, actual: %ld.\n", 3, qp->queues[2].size());
    printf("Queue 3 expected: %d, actual: %ld.\n", 0, qp->queues[3].size());
    printf("Queue 4 expected: %d, actual: %ld.\n", 0, qp->queues[4].size());

    printf("\nTesting complete removal.\n");

    rf::empty_queues(qp);

    printf("Queue 0 expected: %d, actual: %ld.\n", 0, qp->queues[0].size());
    printf("Queue 1 expected: %d, actual: %ld.\n", 0, qp->queues[1].size());
    printf("Queue 2 expected: %d, actual: %ld.\n", 0, qp->queues[2].size());
    printf("Queue 3 expected: %d, actual: %ld.\n", 0, qp->queues[3].size());
    printf("Queue 4 expected: %d, actual: %ld.\n", 0, qp->queues[4].size());

    printf("\nAdding things to queues.\n");

    rf::add_to_queue(true, "image1.txt", 0, qp, 0);
    rf::add_to_queue(true, "image2.txt", 1, qp, 0);
    rf::add_to_queue(true, "image3.txt", 2, qp, 0);
    rf::add_to_queue(true, "image4.txt", 2, qp, 0);

    rf::add_to_queue(false, "message 1", 0, qp, 0);
    rf::add_to_queue(false, "message 2", 1, qp, 0);
    rf::add_to_queue(false, "message 3", 2, qp, 0);
    rf::add_to_queue(false, "message 4", 2, qp, 0);

    printf("\nTesting saving to file.\n");

    rf::save_queues_package(qp, "qp.txt");

    printf("Queue 0 expected: %d, actual: %ld.\n", 2, qp->queues[0].size());
    printf("Queue 1 expected: %d, actual: %ld.\n", 2, qp->queues[1].size());
    printf("Queue 2 expected: %d, actual: %ld.\n", 4, qp->queues[2].size());
    printf("Queue 3 expected: %d, actual: %ld.\n", 0, qp->queues[3].size());
    printf("Queue 4 expected: %d, actual: %ld.\n", 0, qp->queues[4].size());

    // clear memory
    rf::cleanup(qp);

    printf("\nTesting loading from file.\n");

    rf::QueuesPackage* qp2 = rf::load_queues_package("qp.txt");

    printf("Check values.\n");

    rf::cleanup(qp2);

    return true;
}

bool run_scenario_tests(){
    bool success_scenario_1 = test_scenario_1();

    return success_scenario_1;
}

int main(){
    printf("Running individual tests.\n");
    bool success = run_individual_tests();
    printf("Individual tests overall success: %d.\n", success);

    printf("\n\n\n\n\nRunning scenario tests.\n");
    success = run_scenario_tests();
    printf("Scenario tests overall success: %d.\n", success);

    return 0;
}