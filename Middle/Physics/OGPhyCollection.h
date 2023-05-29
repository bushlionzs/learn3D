#ifndef OGPhyCollection_h__
#define OGPhyCollection_h__


namespace Orphigine
{
	class PhyActor;

	class _OrphigineExport PhyCollection
	{
	public:
		PhyCollection();
		virtual ~PhyCollection();

		void						addActor(PhyActor* actor);

		unsigned int				getNumActors() const;

		const PhyActor*				getActor(unsigned int actorIndex) const;

		void						instantiate();
	protected:
		std::vector<PhyActor*>		m_actors;
	private:
	};
}
#endif // OGPhyCollection_h__
