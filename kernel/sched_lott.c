/*
 * TODO: Declare sched_class for this project3
 * 	 Implement each basic operation fucntions of this scheduler
 * 	 Add *original* features
 *
 * Algorithm: Lottery scheduling (based on RNG)
 *
 */


static const struct sched_class lott_sched_class;




/*
 * All the scheduling class methods:
 */
static const struct sched_class lott_sched_class = {
	.next			= &fair_sched_class,
	.enqueue_task		= enqueue_task_lott,
	.dequeue_task		= dequeue_task_lott,
	.yield_task		= yield_task_lott,

	.check_preempt_curr	= check_preempt_wakeup,

	.pick_next_task		= pick_next_task_lott,
	.put_prev_task		= put_prev_task_lott,

#ifdef CONFIG_SMP
	.select_task_rq		= select_task_rq_lott,

	.load_balance		= load_balance_lott,
	.move_one_task		= move_one_task_lott,
	.rq_online		= rq_online_lott,
	.rq_offline		= rq_offline_lott,

	.task_waking		= task_waking_lott,
#endif

	.set_curr_task          = set_curr_task_lott,
	.task_tick		= task_tick_lott,
	.task_fork		= task_fork_lott,

	.prio_changed		= prio_changed_lott,
	.switched_to		= switched_to_lott,

	.get_rr_interval	= get_rr_interval_lott,

#ifdef CONFIG_LOTT_GROUP_SCHED
	.moved_group		= moved_group_lott,
#endif
};

