module left_shift_register(
    input clk,
    input reset,
    input write,
    input [3:0] D,
    output reg [3:0] Q
    );

    integer i;
    always @(posedge clk)
    begin
        if (!reset)
        begin
            Q <= 0;
        end
        else
        begin
            if (write)
            begin
                Q <= D;
            end
            else
            begin
                for (i = 0; i < 3; i = i + 1)
                begin
                    Q[i + 1] <= Q[i];
                end
                Q[0] <= Q[3];
            end
        end
    end
endmodule