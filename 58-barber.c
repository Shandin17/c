// pseudocode
int seats = TOTAL_SEATS_COUNT;
mutex seats_mutex; // seats protection
semaphore customers; // equal to number of waiting clients
bin_semaphore barber; // block clients in queue
bin_semaphore client; // blocks barber until client will sit on working chair
bin_semaphore seat_belt; // blocks client in working chair till haircut will be finished

// barber
for (;;) {
    down(customers); // sleep if customers == 0
    lock(seats_mutex);
    up(barber); // invite client
    seats++;
    unlock(seats_mutex);
    down(client);
    BARBER_WORK();
    up(seat_belt);
}

// client
lock(seats_mutex);
if (seats > 0) {
    seats--;
    up(customers); // if barber were sleeping, this will make him awake
    unlock(seats_mutex);
    down(barber); // if barber is busy then wait
    CUSTOMER_PREPARE(); // sit client in chair
    up(client); // allow to start haircut
    down(seat_belt); // waits till haircut will be finished
} else {
    // there are no seats. We have to leave
    unlock(seats_mutex);
}



