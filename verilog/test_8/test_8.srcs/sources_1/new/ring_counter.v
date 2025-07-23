`timescale 1ns / 1ps

// Basic Ring Counter
module ring_counter (
    input clk, reset_p,
    output reg [3:0] q
    );

    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            q <= 4'b0001;                   // 초기값 설정
        end
        else begin
            case (q)
                4'b0001 : q <= 4'b0010;
                4'b0010 : q <= 4'b0100;
                4'b0100 : q <= 4'b1000;
                4'b1000 : q <= 4'b0001;
                default : q <= 4'b0001;     // 기본값 설정
            endcase
        end
    end
endmodule

// Shift Ring Counter
module ring_counter_shift (
    input clk, reset_p,
    output reg [3:0] q
    );

    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            q <= 4'b0001;                   // 초기값 설정
        end
        else begin
            if (q >= 4'b1000 || q == 4'b0000) begin
                q <= 4'b0001;
            end
            else begin
                q <= {q[2:0], 1'b0};        // Left Shift
            end
        end
    end
endmodule

// FND 출력 위치 결정용 Ring Counter, Common-Anode
module ring_counter_fnd (
    input clk, reset_p,
    output reg [3:0] q
    );

    reg [16:0] clk_div = 0;     // Clock 분주용
    wire clk_div_p;

    always @(posedge clk) begin
        clk_div <= clk_div + 1;
    end

    // Clock Divide, Edge 검출 통해 분주처럼 작동
    edge_detector_neg ed (.clk(clk), .reset_p(reset_p),
                        .cp(clk_div[10]), .p_edge(clk_div_p));

    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            q <= 4'b1110;
        end
        else if (clk_div_p) begin
            if (q == 4'b0111) begin
                q <= 4'b1110;
            end
            else begin
                q <= {q[2:0], 1'b1};        // Left Shift
            end
        end
    end
endmodule

// LED 출력 Ring Counter
module ring_counter_led (
    input clk, reset_p,
    output reg [15:0] led
    );

    reg [25:0] clk_div = 0;     // Clock 분주용
    wire clk_div_p;

    always @(posedge clk) begin
        clk_div <= clk_div + 1;
    end

    // Clock Divide, Edge 검출 통해 분주처럼 작동
    edge_detector_neg ed (.clk(clk), .reset_p(reset_p),
                        .cp(clk_div[24]), .p_edge(clk_div_p));
    
    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            led = 16'b0000_0000_0000_0001;
        end
        else if (clk_div_p) begin
            led = {led[14:0], led[15]};     // Left Shift
        end
    end
endmodule