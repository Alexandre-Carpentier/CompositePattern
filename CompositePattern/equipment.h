#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <Windows.h>

namespace equipment {
	/*
	New measurement type
	*/
	typedef struct {
		std::string MeasurementName;
		double value;
	}MEASUREMENT, * PMEASURMENT;

	/*
	Measurement component
	*/
	class Measurement {
	public:
		virtual ~Measurement() {}
		virtual void add(Measurement*) {}
		virtual void remove(Measurement*) {}

		Measurement* GetParent() { return this->ClassParent; }
		void SetParent(Measurement* parent) { this->ClassParent = parent; }
		virtual bool IsComposite() const { return false; }
		virtual std::vector<MEASUREMENT> GetValue() = 0;

		Measurement* ClassParent = nullptr;
	protected:

	private:
	};

	/*
	Oscope Single Measurements
	*/
	class Oscope : public Measurement {
	public:
		Oscope()
		{
			res.push_back({ "Oscope tension", 12.0 });
		}
		std::vector<MEASUREMENT> GetValue()/*const*/ override { std::cout << "Oscope" << std::endl; return res; }
	protected:
		std::vector<MEASUREMENT> res;
	private:
	};

	/*
	Oscope Single Measurements
	*/
	class Multimeter : public Measurement {
	public:
		Multimeter()
		{
			res.push_back({ "Multimeter tension", 13.0 });
		}
		std::vector<MEASUREMENT> GetValue() /*const*/ override { std::cout << "Multimeter" << std::endl; return res; }
	protected:
		std::vector<MEASUREMENT> res;
	private:
	};

	/*
	Composite is branch of multiple measurements
	*/
	class Composite : public Measurement {
	protected:
		std::list<Measurement*> child;
		std::vector<MEASUREMENT> composite_result;
	public:

		virtual void add(Measurement* meas) override {
			this->child.push_back(meas);
			meas->SetParent(this);
		}

		virtual void remove(Measurement* meas) override {
			child.remove(meas);
			meas->SetParent(nullptr);
		}

		virtual std::vector<MEASUREMENT> GetValue()  override {

			for (auto p : child)
			{
				auto m = p->GetValue();

				for (auto item : m)
				{
					composite_result.push_back({ item.MeasurementName, item.value });
				}
			}
			return composite_result;
		}

		virtual bool IsComposite() const { return true; }

	private:

	};
}