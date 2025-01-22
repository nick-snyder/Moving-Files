module top;
    reg [3:0] data1;

    reg [0:3] data2;

    initial begin

        data1 = 4'b1010;

        data2 = 4'b1010;

        $display ("%d", data1);   

        $display ("%h", data2);      

        $display ("%b", data1[0]); 

        $display (data2[0]);          

    end
endmodule

//module DUT (Y, A, B);
//    output Y;
//    input A, B;
//    and (Y, A, B);
//endmodule