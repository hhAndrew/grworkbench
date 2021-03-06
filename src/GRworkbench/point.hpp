#pragma once

#include <map>
#include <boost/optional.hpp>
#include <memory>
#include "atlas.hpp"
#include "nvector_differential.hpp"

namespace grwb
{

  class point
  {

  public:

    point(const std::shared_ptr<chart>& c, const nvector<double>& x)
      : chart_(c)
    {
      _.insert(make_pair(c, optional<nvector<double> >(x)));
    }

    const optional<nvector<double> > operator[](const std::shared_ptr<chart>& c) const
    {
      std::map<std::shared_ptr<chart>, optional<nvector<double> > >::const_iterator i = _.find(c);
      if (i != _.end())
      {
        return i->second;
      }
      else
      {
        for (i = _.begin(); i != _.end(); ++i)
        {
          if (i->second)
          {
            std::map<pair<std::shared_ptr<chart>, std::shared_ptr<chart> >, std::shared_ptr<inter_chart_map> >::const_iterator j = inter_chart_maps().find(make_pair(i->first, c));
            if (j != inter_chart_maps().end())
            {
              return _.insert(make_pair(c, value((*j->second)(make_gradient(*i->second))))).first->second;
            }
          }
        }
			}
      return _.insert(make_pair(c, optional<nvector<double> >())).first->second;
    }

    //const std::shared_ptr<atlas>& context() const
    //{
    //  return atlas_;
    //}
    
    const std::shared_ptr<chart>& valid_chart() const
    {
      return chart_;
    }
    
  private:
    //const std::shared_ptr<atlas> atlas_;
    const std::shared_ptr<chart> chart_;
    mutable std::map<std::shared_ptr<chart>, optional<nvector<double> > > _;
    point& operator=(const point&);

  };  
}

