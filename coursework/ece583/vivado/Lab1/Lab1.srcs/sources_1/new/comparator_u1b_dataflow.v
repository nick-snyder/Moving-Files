module comparator_u1b_dataflow(greater, equal, less, a, b);

    output greater, equal, less;
    input a, b;
    
    assign greater = a & ~b;
    assign equal = ~(greater | less);
    assign less = ~a & b;

endmodule