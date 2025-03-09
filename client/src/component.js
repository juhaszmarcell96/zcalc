class IComponent {
    constructor (x, y) {
        this.x = x - (x % grid_size);
        this.y = y - (y % grid_size);
    }

    draw (context) {
        console.log('ERROR : "draw" function not overloaded');
    }

    is_inside(pos_x, pos_y) {
        console.log('ERROR : "is_inside" function not overloaded');
    }

    get_terminal_at (pos_x, pos_y) {
        console.log('ERROR : "get_terminal_at" function not overloaded');
    }

    do_stuff () {
        console.log('ERROR : "do_stuff" function not overloaded');
    }

    get_terminals () {
        console.log('ERROR : "get_terminals" function not overloaded');
    }

    /* propagate the states of the terminals to each other based on the internal logic of the component */
    /* the function should return true if the state of any of its terminals changes during the process, false otherwise */
    propagate () {
        console.log('ERROR : "propagate" function not overloaded');
    }

    /* reset the states of the terminals */
    reset_terminals () {
        console.log('ERROR : "reset_terminals" function not overloaded');
    }

    /* the component should check the states of its terminals and perform an appropriate action */
    /* e.g.: for a lamp, if terminal L and N have the states L2 and N respectively, it should turn on */
    /*       and it should show some error message if the terminals are not connected the way they should be */
    /* the function should return whether the component changed in a way that new connections appeared */
    check_terminals () {
        console.log('ERROR : "check_terminals" function not overloaded');
    }
};