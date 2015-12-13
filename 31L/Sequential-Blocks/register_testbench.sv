module reg_tb();
	parameter size = 31;

	logic   [size:0] data_in;  
	logic   [size:0] data_out; // 15
	logic	[size:0] prev_data;

	bit clk;  
	bit rst_a;
	bit rst_s;
	bit inc;
	bit we;

	initial begin
		clk =0;
		rst_a =1;
		rst_s =0;
		inc =0;
		prev_data =0;
		we =1;
		#41;
		rst_a = 0;
		#40;
		rst_s = 1;
		#40;
		rst_s = 0;
		#40;
		we = 0;
		#40;
		inc =1;
		#40;
		$finish;
	end

	always #10 clk = ~clk;
   

	always @(negedge clk) begin // Sending Data to C Program
		prev_data = data_out;
		data_in = $urandom % 16;
		$display("write data: %b\n", data_in); 
	end

   // generate the rtl output
   regstr L1( .clk(clk), .rst_a(rst_a), .rst_s(rst_s), 
   .inc(inc), .we(we), .inp(data_in), .datadout(data_out)); 

   //compare expected output and rtl output
	always @(rst_a) 
	begin
		if (rst_a == 1) 
		  begin
			if (data_out == 0)
			  begin
				$display("%t: PASS, Input: %b, Output (EXP/ACT) (%b/%b)", $time, data_in, 0, data_out);
			  end 
			else 
			  begin
				$display("%t: FAIL, Input: %b, Output (EXP/ACT) (%b/%b)", $time, data_in, 0, data_out);
			  end
		  end
	end

	always @(posedge clk) 
	#5
	  begin
		if (rst_a == 1 || rst_s == 1)
  		  begin
			if (data_out == 0) 
			  begin
				$display("%t: PASS, Input: %b, Output (EXP/ACT) (%b/%b)", $time, data_in, 0, data_out);
			  end 
			else 
			  begin
				$display("%t: FAIL, Input: %b, Output (EXP/ACT) (%b/%b)", $time, data_in, 0, data_out);
			  end
		  end 
		else if(inc == 1)
		  begin	
			if (data_out == prev_data + 1)
			  begin
				$display("%t: PASS, Input: %b, Output (EXP/ACT) (%b/%b)", $time, data_in, prev_data+1, data_out);
			  end 
			else 
			  begin
				$display("%t: FAIL, Input: %b, Output (EXP/ACT) (%b/%b)", $time, data_in, prev_data+1, data_out);
			  end
		  end 
		else if(we == 1)
		  begin	
			if (data_out == data_in)
			  begin
				$display("%t: PASS, Input: %b, Output (EXP/ACT) (%b/%b)", $time, data_in, data_in, data_out);
			  end 
			else 
			  begin
				$display("%t: FAIL, Input: %b, Output (EXP/ACT) (%b/%b)", $time, data_in, data_in, data_out);
			  end
		  end
		else if(we == 0)
		  begin	
			if (data_out == prev_data)
			  begin
				$display("%t: PASS, Input: %b, Output (EXP/ACT) (%b/%b)", $time, data_in, prev_data, data_out);
			  end 
			else 
			  begin
				$display("%t: FAIL, Input: %b, Output (EXP/ACT) (%b/%b)", $time, data_in, prev_data, data_out);
			  end
		  end 				  
	  end
endmodule
