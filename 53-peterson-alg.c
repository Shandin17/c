// work with


//first

void enter_section() {
    interested[0] = TRUE;
    who_waits = 0;
    while (who_waits == 0 && interested[1]) {}
    // work with critical section
}
void leave_section() {
    interested[0] = FALSE;
}


//second
void enter_section() {
    interested[1] = TRUE;
    who_waits = 1;
    while (who_waits == 1 && interested[0]) {}
    // work with critical section
}
void leave_section() {
    interested[1] = FALSE;
}

