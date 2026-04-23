	int bente = 3800;
	while (data->stack_b && bente) // alles naar b: 73_50 0-49(random) 74_99
	{
		if ((data->stack_b->sorted_index >= data->tq && \
				data->stack_b->sorted_index <= data->tq + 2) && \
				data->stack_b->sorted_index > data->three_quarter) // 75->99 
			upper_quarter_B(data);
		else if ((data->stack_a->sorted_index >= data->h && \
				data->stack_b->sorted_index <= data->h + 2) && \
				data->stack_b->sorted_index <= data->three_quarter) // 50->74	
			lower_quarter_B(data);
		else // was niet de goeie
			rb(&data->stack_b);
		bente--;
	}
