module mux_2c_1b_dataflow(out, s, a, b);

    output out;         // mux output
    input  s, a, b;     // mux inputs
    
    assign out = (a & (~ s)) | (b & s); 

endmodule 