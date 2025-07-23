`timescale 1ns / 1ps

// Negative edge Edge Detector
module edge_detector_neg (
    input clk, reset_p, cp,     // Clock, Reset, Input Signal 감지
    output p_edge, n_edge       // Rising, Falling 감지 출력
    );

    reg ff_cur, ff_old;         // cp 현재값과 이전값 저장할 Flip-Flop

    always @(negedge clk or posedge reset_p) begin
        if (reset_p) begin          // Reset Flip-Flop 초기화
            ff_cur <= 1'b0;
            ff_old <= 1'b0;
        end
        else begin                  // 이전값 저장하고 현재값 갱신
            ff_old <= ff_cur;
            ff_cur <= cp;
        end
    end

    // Rising 감지, 이전 0, 현재 1 이면 p_edge = 1
    assign p_edge = ({ff_cur, ff_old} == 2'b10) ? 1'b1 : 1'b0;
    // Falling 감지, 이전 1, 현재 0 이면 n_edge = 1
    assign n_edge = ({ff_cur, ff_old} == 2'b01) ? 1'b1 : 1'b0;
endmodule

// Positive edge Edge Detector
module edge_detector_pos (
    input clk, reset_p, cp,     // Clock, Reset, Input Signal 감지
    output p_edge, n_edge       // Rising, Falling 감지 출력
    );

    reg ff_cur, ff_old;         // cp 현재값과 이전값 저장할 Flip-Flop

    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin          // Reset Flip-Flop 초기화
            ff_cur <= 1'b0;
            ff_old <= 1'b0;
        end
        else begin                  // 이전값 저장하고 현재값 갱신
            ff_old <= ff_cur;
            ff_cur <= cp;
        end
    end

    // Rising 감지, 이전 0, 현재 1 이면 p_edge = 1
    assign p_edge = ({ff_cur, ff_old} == 2'b10) ? 1'b1 : 1'b0;
    // Falling 감지, 이전 1, 현재 0 이면 n_edge = 1
    assign n_edge = ({ff_cur, ff_old} == 2'b01) ? 1'b1 : 1'b0;
endmodule
