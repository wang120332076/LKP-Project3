/*
 * TODO: Declare sched_class for this project3
 * 	 Implement each basic operation fucntions of this scheduler
 * 	 Add *original* features
 *
 * Algorithm: Lottery scheduling (based on RNG)
 *
 */

static const struct sched_class lott_sched_class;

/* Initialize parameters in rq */
void init_lott_rq(struct lott_rq *lott_rq)
{
	lott_rq->total_tickets = 0;
	INIT_LIST_HEAD(&(lott_rq->task_list));
}

/* Enqueue a runnable task:
 *  1. Pull out lott_task descriptor in overall task list (ignore runnability)
 *  2. Put lott_task in queue (list) according to its ticket#
 *  3. Give an initial tickets <- *SHOULD NOT BE HERE (INITIALIZATION)
 *  4. Record total ticket#
 */
static void enqueue_task_lott(struct rq *rq, struct task_struct *p, int wakeup, bool head)
{
	struct lott_rq *lott_rq = &rq->lott;
	

	if (p) {
		rq->lott.total_tickets += p->tickets;
		list_add_tail(&p->elem, &lott_rq->task_list);		
	}

	printk(KERN_ALERT "enqueue_task_lott\n");
}

/* */
static void dequeue_task_lott(struct rq *rq, struct task_struct *p, int sleep)
{
	//struct lott_rq *lott_rq = &rq->lott;

	if (p) {
		rq->lott.total_tickets -= p->tickets;
		list_del(&p->elem);
	}

	printk(KERN_ALERT "dequeue_task_lott\n");
}

/* */
static void yield_task_lott(struct rq *rq)
{
}

/* */
static struct task_struct *pick_next_task_lott(struct rq *rq)
{
	struct lott_rq *lott_rq = &rq->lott;
	struct list_head *first;
	struct task_struct *ret = NULL;
	/* First element is head->next because head is a sentinel node */
	
	if (list_empty(&lott_rq->task_list))
		goto out;

        first = lott_rq->task_list.next;
	ret = list_entry(first, struct task_struct, elem);
out:
	//printk(KERN_ALERT "number of tickets is %d\n", lott_rq->total_tickets);
	//printk(KERN_ALERT "picking next task\n");
	return ret;
}

static void check_preempt_curr_lott(struct rq *rq, struct task_struct *p, int flags)
{
}

static void put_prev_task_lott(struct rq *rq, struct task_struct *prev)
{
}

#ifdef CONFIG_SMP
static int select_task_rq_lott(struct rq *rq, struct task_struct *p, int sd_flag, int flags)
{
	return 0;
}

static unsigned long load_balance_lott(struct rq *this_rq, int this_cpu, struct rq *busiest,
                 unsigned long max_load_move,
                 struct sched_domain *sd, enum cpu_idle_type idle,
                 int *all_pinned, int *this_best_prio)
{
       return 0;
}

static int move_one_task_lott(struct rq *this_rq, int this_cpu, struct rq *busiest,
                  struct sched_domain *sd, enum cpu_idle_type idle)
{
       return 0;
}

static void pre_schedule_lott(struct rq *this_rq, struct task_struct *task)
{
}

static void post_schedule_lott(struct rq *this_rq)
{
}

static void set_cpus_allowed_lott(struct task_struct *p,
                                  const struct cpumask *newmask)
{
}

/* Assumes rq->lock is held */
static void rq_online_lott(struct rq *rq)
{

}

/* Assumes rq->lock is held */
static void rq_offline_lott(struct rq *rq)
{

}

static void task_waking_lott(struct rq *rq, struct task_struct *p)
{
}

static void task_woken_lott(struct rq *rq, struct task_struct *p)
{
}

#endif

static void set_curr_task_lott(struct rq *rq)
{

}

static void task_tick_lott(struct rq *rq, struct task_struct *p, int queued)
{
	static int tick_count = 0;
	if (tick_count++ == 4)
	{
		tick_count = 0;
		resched_task(p);
		printk(KERN_ALERT "Rescheduling task\n");
	}	
}

static void task_fork_lott(struct task_struct *p)
{
}

/*
 * Priority of the task has changed. This may cause
 * us to initiate a push or pull.
 */
static void prio_changed_lott(struct rq *rq, struct task_struct *p,
                           int oldprio, int running)
{

}

static void switched_from_lott(struct rq *rq, struct task_struct *p,
                           int running)
{
}

static void switched_to_lott(struct rq *rq, struct task_struct *p,
                           int running)
{
}

unsigned int get_rr_interval_lott(struct rq *rq, struct task_struct *task)
{
	return 0;
}

void moved_group_lott(struct task_struct *p, int on_rq)
{
}
/*
 * All the scheduling class methods:
 */
static const struct sched_class lott_sched_class = {
	.next			= &fair_sched_class,
	.enqueue_task		= enqueue_task_lott,
	.dequeue_task		= dequeue_task_lott,
	.yield_task		= yield_task_lott,

	.check_preempt_curr	= check_preempt_curr_lott,

	.pick_next_task		= pick_next_task_lott,
	.put_prev_task		= put_prev_task_lott,

#ifdef CONFIG_SMP
	.select_task_rq		= select_task_rq_lott,

	.load_balance		= load_balance_lott,
	.move_one_task		= move_one_task_lott,
	.pre_schedule		= pre_schedule_lott,
	.post_schedule		= post_schedule_lott,
	.set_cpus_allowed	= set_cpus_allowed_lott,
	.rq_online		= rq_online_lott,
	.rq_offline		= rq_offline_lott,

	.task_waking		= task_waking_lott,
	.task_woken		= task_woken_lott,
#endif

	.set_curr_task          = set_curr_task_lott,
	.task_tick		= task_tick_lott,
	.task_fork		= task_fork_lott,

	.prio_changed		= prio_changed_lott,
	.switched_from		= switched_from_lott,
	.switched_to		= switched_to_lott,

	.get_rr_interval	= get_rr_interval_lott,

#ifdef CONFIG_LOTT_GROUP_SCHED
	.moved_group		= moved_group_lott,
#endif
};

