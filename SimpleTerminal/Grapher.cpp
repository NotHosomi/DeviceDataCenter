#include "Grapher.h"
#include <matplot/matplot.h>
#include <algorithm>

Grapher::Grapher(std::filesystem::path outputDir) :
	m_PlotDir(outputDir)
{

}

void Grapher::GraphEIS(std::string sId, T_ErrorBarD tZ, T_ErrorBarD tPhase)
{
	matplot::error_bar_handle magnitudePlot = matplot::errorbar(tZ.x, tZ.y, tZ.err);
	matplot::gca()->x_axis().scale(matplot::axis_type::axis_scale::log);
	matplot::gca()->y_axis().scale(matplot::axis_type::axis_scale::log);

	matplot::hold(true);
	matplot::error_bar_handle phasePlot = matplot::errorbar(tPhase.x, tPhase.y, tPhase.err);
	phasePlot->use_y2(true);
	phasePlot->y_positive_delta(tPhase.err);
	matplot::y2lim({ 0,90 });
	
	std::string path = m_PlotDir.string() + "/" + sId + "/Plots/";
	std::filesystem::create_directories(path);
	matplot::save(path + "EIS.png");
}

void Grapher::GraphCV(std::string path, std::string Id)
{
}

void Grapher::GraphCIL(std::string path, std::string Id)
{
}
