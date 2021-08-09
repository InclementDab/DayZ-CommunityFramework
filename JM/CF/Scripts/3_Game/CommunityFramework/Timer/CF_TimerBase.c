class CF_TimerBase : Managed
{
	private static ref CF_TimerBase s_Head;
	private ref CF_TimerBase m_Next;
	private CF_TimerBase m_Prev;
	private bool m_IsActive;
	private bool m_Destroy;

	protected float m_Interval; // Seconds
	protected float m_DeltaTime; // Seconds
	protected int m_TimeElapsedMS; // Milliseconds

	protected void CF_TimerBase()
	{
		OnCreate();
	}

	void ~CF_TimerBase()
	{
		Stop();

		OnDestroy();
	}

	void Start()
	{
		if (m_IsActive) return;

		m_IsActive = true;

		if (s_Head == null)
		{
			s_Head = this;
		}
		else
		{
			m_Next = s_Head;
			s_Head.m_Prev = this;
			s_Head = this;
		}

		OnStart();
	}

	/**
	 * Stops the timer, decrementing the reference count.
	 */
	void Stop()
	{
		if (!m_IsActive) return;

		m_IsActive = false;

		if (s_Head == this)
		{
			s_Head = m_Next;
			if (s_Head) s_Head.m_Prev = null;
		}
		else
		{
			m_Prev.m_Next = m_Next;
			if (m_Next) m_Next.m_Prev = m_Prev;
		}

		OnStop();
	}

	void Destroy()
	{
		m_Destroy = true;
	}

	/**
	 * The time between each 'OnTick' call, in seconds.
	 */
	void SetInterval(float interval)
	{
		m_Interval = interval;
		if (m_Interval < 0) m_Interval = 0;
	}

	/**
	 * The time between each 'OnTick' call, in seconds.
	 */
	float GetInterval()
	{
		return m_Interval;
	}

	/**
	 * The total time elapsed for this timer, in milliseconds.
	 */
	void SetTimeElapsedMS(int elapsed)
	{
		m_TimeElapsedMS = elapsed;
	}

	/**
	 * The total time elapsed for this timer, in milliseconds.
	 */
	int GetTimeElapsedMS()
	{
		return m_TimeElapsedMS;
	}

	/**
	 * The total time elapsed for this timer, in seconds.
	 */
	float GetTimeElapsed()
	{
		return m_TimeElapsedMS / 1000.0;
	}

	protected void OnCreate();

	protected void OnDestroy();

	protected void OnStart();

	protected void OnStop();

	protected void OnTick(float dt);

	protected void OnUpdate(float dt)
	{
		m_TimeElapsedMS += dt * 1000.0;
		m_DeltaTime += dt;

		if (m_DeltaTime >= m_Interval)
		{
			OnTick(m_DeltaTime);
			m_DeltaTime = 0;
		}
	}

	static void _Update(float dt)
	{
		CF_TimerBase current = s_Head;
		CF_TimerBase next = null;
		while (current)
		{
			next = current.m_Next;

			current.OnUpdate(dt);

			if (current.m_Destroy)
			{
				// Destructor will remove the timer from the linked list, joining the adjacent variables.
				delete current;
			}
			
			current = next;
		}
	}
};
