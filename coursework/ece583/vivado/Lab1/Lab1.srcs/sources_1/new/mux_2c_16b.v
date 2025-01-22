module mux_2c_16b(out, s, a, b);

    output[0:15] out;
    input[0:15] a, b;
    input s;
    
    mux_2c_1b_dataflow bit0(out[0], s, a[0], b[0]);
    mux_2c_1b_dataflow bit1(out[1], s, a[1], b[1]);
    mux_2c_1b_dataflow bit2(out[2], s, a[2], b[2]);
    mux_2c_1b_dataflow bit3(out[3], s, a[3], b[3]);
    mux_2c_1b_dataflow bit4(out[4], s, a[4], b[4]);
    mux_2c_1b_dataflow bit5(out[5], s, a[5], b[5]);
    mux_2c_1b_dataflow bit6(out[6], s, a[6], b[6]);
    mux_2c_1b_dataflow bit7(out[7], s, a[7], b[7]);
    mux_2c_1b_dataflow bit8(out[8], s, a[8], b[8]);
    mux_2c_1b_dataflow bit9(out[9], s, a[9], b[9]);
    mux_2c_1b_dataflow bit10(out[10], s, a[10], b[10]);
    mux_2c_1b_dataflow bit11(out[11], s, a[11], b[11]);
    mux_2c_1b_dataflow bit12(out[12], s, a[12], b[12]);
    mux_2c_1b_dataflow bit13(out[13], s, a[13], b[13]);
    mux_2c_1b_dataflow bit14(out[14], s, a[14], b[14]);
    mux_2c_1b_dataflow bit15(out[15], s, a[15], b[15]);

endmodule