`timescale 1ns / 1ps

module tb_decoder_2X4;
    reg [1:0] code;
    wire [3:0] signal;

    // decoder_2X4_behavioral dut (.code(code), .signal(signal));
    decoder_2X4_structural dut (.code(code), .signal(signal));
    // decoder_2X4_dataflow dut (.code(code), .signal(signal));

    initial begin
        $display("Time\tcode | signal");
        $monitor("%4d\t %b  |  %b", $time, code, signal);

        code = 2'b00; #10;
        code = 2'b01; #10;
        code = 2'b10; #10;
        code = 2'b11; #10;
        $finish;
    end
endmodule

module tb_encoder_4X2;
    reg [3:0] signal;       // Input Signal
    wire [1:0] code;        // Output Code

    encoder_4X2_behavioral dut (.signal(signal), .code(code));
    // encoder_4X2_structural dut (.signal(signal), .code(code));
    // encoder_4X2_dataflow dut (.signal(signal), .code(code));

    initial begin
        signal = 4'b0001; #10;
        signal = 4'b0010; #10;
        signal = 4'b0100; #10;
        signal = 4'b1000; #10;
        signal = 4'b0000; #10;
        signal = 4'b0011; #10;
        $finish;
    end

    initial begin
        $display("Time\tsignal code");
        $monitor("%4d\t %b   %b", $time, signal, code);
    end
endmodule